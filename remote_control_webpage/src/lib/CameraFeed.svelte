<script lang="ts">
	import { untrack } from 'svelte';

	type FeedStatus = 'idle' | 'connecting' | 'streaming' | 'error' | RTCPeerConnectionState;

	let { name, label = name }: { name: string; label?: string } = $props();

	let videoEl = $state<HTMLVideoElement | null>(null);
	let status = $state<FeedStatus>('idle');
	let recording = $state(false);

	// Non-reactive — read inside $effect cleanup, must not trigger re-runs
	let pc: RTCPeerConnection | null = null;
	let sessionUrl: string | null = null;
	let reconnectTimer: ReturnType<typeof setTimeout> | null = null;
	let recorder: MediaRecorder | null = null;
	let isRecording = false;
	let chunks: BlobPart[] = [];

	function whepUrl(): string {
		const s = location.protocol === 'https:' ? 'https' : 'http';
		return `${s}://${location.hostname}:8889/${name}/whep`;
	}

	async function start(): Promise<void> {
		stop();
		status = 'connecting';

		pc = new RTCPeerConnection({ iceServers: [{ urls: 'stun:stun.l.google.com:19302' }] });
		pc.ontrack = (e) => {
			if (videoEl) videoEl.srcObject = e.streams[0];
		};
		pc.onconnectionstatechange = () => {
			if (!pc) return;
			status = pc.connectionState === 'connected' ? 'streaming' : pc.connectionState;
			if (['failed', 'disconnected', 'closed'].includes(pc.connectionState)) {
				scheduleReconnect();
			}
		};

		const offer = await pc.createOffer({ offerToReceiveVideo: true, offerToReceiveAudio: false });
		await pc.setLocalDescription(offer);

		const res = await fetch(whepUrl(), {
			method: 'POST',
			headers: { 'Content-Type': 'application/sdp' },
			body: offer.sdp
		});
		if (!res.ok) throw new Error(`WHEP ${res.status}`);

		sessionUrl = res.headers.get('location') || res.headers.get('Location');
		await pc.setRemoteDescription({ type: 'answer', sdp: await res.text() });
		status = 'streaming';
	}

	function stop(): void {
		if (isRecording) stopRecording();
		pc?.close();
		pc = null;
		if (videoEl?.srcObject) {
			(videoEl.srcObject as MediaStream).getTracks().forEach((t) => t.stop());
			videoEl.srcObject = null;
		}
		if (sessionUrl) {
			fetch(sessionUrl, { method: 'DELETE' }).catch(() => {});
			sessionUrl = null;
		}
		status = 'idle';
	}

	function scheduleReconnect(): void {
		if (reconnectTimer) return;
		reconnectTimer = setTimeout(() => {
			reconnectTimer = null;
			start().catch(() => {
				status = 'error';
				scheduleReconnect();
			});
		}, 2000);
	}

	function startRecording(): void {
		if (!videoEl?.srcObject) return;
		chunks = [];
		const mimeType = MediaRecorder.isTypeSupported('video/webm;codecs=vp9')
			? 'video/webm;codecs=vp9'
			: 'video/webm';
		recorder = new MediaRecorder(videoEl.srcObject as MediaStream, { mimeType });
		recorder.ondataavailable = (e) => {
			if (e.data.size > 0) chunks.push(e.data);
		};
		recorder.onstop = () => {
			const blob = new Blob(chunks, { type: 'video/webm' });
			const url = URL.createObjectURL(blob);
			const a = document.createElement('a');
			a.href = url;
			a.download = `${name}_${new Date().toISOString().replace(/[:.]/g, '-')}.webm`;
			a.click();
			URL.revokeObjectURL(url);
		};
		recorder.start();
		isRecording = true;
		recording = true;
	}

	function stopRecording(): void {
		isRecording = false;
		recording = false;
		recorder?.stop();
		recorder = null;
	}

	// untrack prevents reactive reads inside start()/stop() from re-triggering this effect
	$effect(() => {
		untrack(() => {
			start().catch(() => {
				status = 'error';
				scheduleReconnect();
			});
		});
		return () => {
			untrack(() => {
				if (reconnectTimer) clearTimeout(reconnectTimer);
				stop();
			});
		};
	});
</script>

<div class="feed">
	<div class="feed-header">
		<span class="feed-label">{label}</span>
		<div class="feed-right">
			{#if recording}
				<span class="rec-indicator">● REC</span>
			{/if}
			<span class="feed-status" class:ok={status === 'streaming'} class:err={status === 'error'}>
				{status}
			</span>
		</div>
	</div>
	<video bind:this={videoEl} autoplay playsinline muted></video>
	<div class="feed-controls">
		{#if !recording}
			<button onclick={startRecording} disabled={status !== 'streaming'}>● Record</button>
		{:else}
			<button class="stop" onclick={stopRecording}>■ Stop & Save</button>
		{/if}
	</div>
</div>

<style>
	.feed {
		background: #13162a;
		border: 1px solid #222535;
		border-radius: 6px;
		overflow: hidden;
		min-width: 320px;
		flex: 1;
	}

	.feed-header {
		display: flex;
		justify-content: space-between;
		align-items: center;
		padding: 7px 12px;
		background: #0d0f1a;
		border-bottom: 1px solid #222535;
		font-size: 0.75rem;
		text-transform: uppercase;
		letter-spacing: 0.1em;
	}

	.feed-label { color: #7eb8f7; }

	.feed-right {
		display: flex;
		align-items: center;
		gap: 10px;
	}

	.rec-indicator {
		color: #f44336;
		font-size: 0.72rem;
		animation: blink 1s step-start infinite;
	}

	@keyframes blink {
		50% { opacity: 0; }
	}

	.feed-status { color: #444; }
	.feed-status.ok { color: #4caf50; }
	.feed-status.err { color: #f44336; }

	video {
		display: block;
		width: 100%;
		aspect-ratio: 16/9;
		background: #000;
	}

	.feed-controls { padding: 8px 12px; }

	button {
		padding: 4px 14px;
		border: 1px solid #2a2d3a;
		border-radius: 4px;
		background: #1a1d27;
		color: #aaa;
		cursor: pointer;
		font-size: 0.78rem;
		font-family: inherit;
		transition: border-color 0.15s, color 0.15s;
	}
	button:hover:not(:disabled) { border-color: #7eb8f7; color: #7eb8f7; }
	button:disabled { opacity: 0.3; cursor: not-allowed; }
	button.stop { border-color: #f44336; color: #f44336; }
	button.stop:hover { border-color: #ff6659; color: #ff6659; }
</style>
