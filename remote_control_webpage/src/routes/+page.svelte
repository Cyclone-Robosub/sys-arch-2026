<script lang="ts">
	import CameraFeed from '$lib/CameraFeed.svelte';

	type RosStatus = 'connected' | 'disconnected' | 'error';

	interface ControllerState {
		x: number;
		y: number;
		rise: number;
		sink: number;
		yaw: number;
		pitch: number;
		cross_button: boolean;
		square_button: boolean;
		triangle_button: boolean;
		circle_button: boolean;
		dpad_down: boolean;
		dpad_left: boolean;
		dpad_up: boolean;
		dpad_right: boolean;
		bumper_left: boolean;
		bumper_right: boolean;
		start: boolean;
		select: boolean;
		joystick_press_left: boolean;
		joystick_press_right: boolean;
	}

	const cams = [
		{ name: 'cam', label: 'Front' },
		{ name: 'left', label: 'Left' },
		{ name: 'right', label: 'Right' },
		{ name: 'down', label: 'Down' }
	] as const;

	type CamName = (typeof cams)[number]['name'];

	let rosStatus = $state<RosStatus>('disconnected');
	let controllerConnected = $state(false);
	let ctrl = $state<ControllerState>({
		x: 0, y: 0, rise: 0, sink: 0, yaw: 0, pitch: 0,
		cross_button: false, square_button: false, triangle_button: false, circle_button: false,
		dpad_down: false, dpad_left: false, dpad_up: false, dpad_right: false,
		bumper_left: false, bumper_right: false, start: false, select: false,
		joystick_press_left: false, joystick_press_right: false
	});
	let show = $state<Record<CamName, boolean>>({ cam: false, left: false, right: false, down: false });

	let controllerPub: RoslibTopic | null = null;
	let animId: number | null = null;

	function dz(v: number, t = 0.1): number {
		return Math.abs(v) > t ? v : 0;
	}

	function poll(): void {
		const gp = navigator.getGamepads()[0];
		if (gp) {
			const b = gp.buttons;
			const next: ControllerState = {
				x: dz(gp.axes[0]),
				y: dz(-gp.axes[1]),
				yaw: dz(gp.axes[2]),
				pitch: dz(-gp.axes[3]),
				rise: b[7].value,
				sink: b[6].value,
				cross_button: b[0].pressed,
				circle_button: b[1].pressed,
				square_button: b[2].pressed,
				triangle_button: b[3].pressed,
				bumper_left: b[4].pressed,
				bumper_right: b[5].pressed,
				select: b[8].pressed,
				start: b[9].pressed,
				joystick_press_left: b[10].pressed,
				joystick_press_right: b[11].pressed,
				dpad_up: b[12].pressed,
				dpad_down: b[13].pressed,
				dpad_left: b[14].pressed,
				dpad_right: b[15].pressed
			};
			ctrl = next;
			controllerPub?.publish(new window.ROSLIB.Message(next));
		}
		animId = requestAnimationFrame(poll);
	}

	$effect(() => {
		const scheme = location.protocol === 'https:' ? 'wss' : 'ws';
		const ros = new window.ROSLIB.Ros({ url: `${scheme}://${location.hostname}:9090` });
		ros.on('connection', () => (rosStatus = 'connected'));
		ros.on('error', () => (rosStatus = 'error'));
		ros.on('close', () => (rosStatus = 'disconnected'));

		controllerPub = new window.ROSLIB.Topic({
			ros,
			name: '/ps5_controller',
			messageType: 'custom_interfaces/msg/Gamepad'
		});
		controllerPub.advertise();

		const onConnect = (): void => {
			controllerConnected = true;
			poll();
		};
		const onDisconnect = (): void => {
			controllerConnected = false;
			if (animId !== null) cancelAnimationFrame(animId);
		};
		window.addEventListener('gamepadconnected', onConnect);
		window.addEventListener('gamepaddisconnected', onDisconnect);

		return () => {
			window.removeEventListener('gamepadconnected', onConnect);
			window.removeEventListener('gamepaddisconnected', onDisconnect);
			if (animId !== null) cancelAnimationFrame(animId);
			controllerPub?.unadvertise();
			ros.close();
		};
	});
</script>

<div class="app">
	<header>
		<span class="title">Robot Control</span>
		<div class="badges">
			<span class="badge" class:ok={rosStatus === 'connected'} class:err={rosStatus === 'error'}>
				ROS {rosStatus}
			</span>
			<span class="badge" class:ok={controllerConnected} class:warn={!controllerConnected}>
				{controllerConnected ? 'Controller' : 'No Controller'}
			</span>
		</div>
	</header>

	<main>
		<section class="panel">
			<h2>Controller</h2>
			<table>
				<tbody>
					{#each Object.entries(ctrl) as [key, val]}
						<tr>
							<td class="key">{key}</td>
							<td class="val" class:active={typeof val === 'number' && Math.abs(val) > 0.05}>{typeof val === 'number' ? val.toFixed(2) : String(val)}</td>
						</tr>
					{/each}
				</tbody>
			</table>
		</section>

		<section class="panel cameras">
			<div class="cameras-header">
				<h2>Cameras</h2>
				<div class="toggles">
					{#each cams as cam}
						<button
							class:active={show[cam.name]}
							onclick={() => (show[cam.name] = !show[cam.name])}
						>
							{cam.label}
						</button>
					{/each}
				</div>
			</div>

			{#if Object.values(show).some(Boolean)}
				<div class="feed-row">
					{#each cams as cam}
						{#if show[cam.name]}
							<CameraFeed name={cam.name} label={cam.label} />
						{/if}
					{/each}
				</div>
			{/if}
		</section>
	</main>
</div>

<style>
	:global(*, *::before, *::after) {
		box-sizing: border-box;
		margin: 0;
		padding: 0;
	}
	:global(body) {
		background: #0d0f17;
		color: #dde1ec;
		font-family: 'Courier New', Courier, monospace;
		min-height: 100vh;
	}

	.app {
		display: flex;
		flex-direction: column;
		min-height: 100vh;
	}

	header {
		display: flex;
		justify-content: space-between;
		align-items: center;
		padding: 10px 16px;
		background: #131620;
		border-bottom: 1px solid #1e2235;
	}

	.title {
		font-size: 0.95rem;
		font-weight: bold;
		color: #7eb8f7;
		letter-spacing: 0.06em;
		text-transform: uppercase;
	}

	.badges {
		display: flex;
		gap: 8px;
	}

	.badge {
		padding: 3px 10px;
		border-radius: 3px;
		font-size: 0.72rem;
		background: #1a1d2a;
		color: #444;
		border: 1px solid #1e2235;
		text-transform: uppercase;
		letter-spacing: 0.06em;
	}
	.badge.ok { color: #4caf50; border-color: #1e3a1e; background: #111a11; }
	.badge.err { color: #f44336; border-color: #3a1e1e; background: #1a1111; }
	.badge.warn { color: #888; }

	main {
		display: grid;
		grid-template-columns: 200px 1fr;
		gap: 12px;
		padding: 12px;
		align-items: start;
	}

	.panel {
		background: #13162a;
		border: 1px solid #1e2235;
		border-radius: 6px;
		padding: 12px;
	}

	h2 {
		font-size: 0.68rem;
		text-transform: uppercase;
		letter-spacing: 0.14em;
		color: #4a6080;
		margin-bottom: 10px;
	}

	table { width: 100%; border-collapse: collapse; }
	td { padding: 4px; font-size: 0.82rem; }
	td.key { color: #3a4a60; text-transform: uppercase; font-size: 0.7rem; }
	td.val { text-align: right; color: #3a4a60; font-variant-numeric: tabular-nums; }
	td.val.active { color: #7eb8f7; }

	.cameras-header {
		display: flex;
		align-items: center;
		gap: 14px;
		margin-bottom: 10px;
	}
	.cameras-header h2 { margin-bottom: 0; }

	.toggles { display: flex; gap: 6px; }

	.toggles button {
		padding: 3px 14px;
		border: 1px solid #1e2235;
		border-radius: 4px;
		background: #13162a;
		color: #444;
		cursor: pointer;
		font-size: 0.75rem;
		font-family: inherit;
		text-transform: uppercase;
		letter-spacing: 0.08em;
		transition: all 0.15s;
	}
	.toggles button:hover { border-color: #7eb8f7; color: #7eb8f7; }
	.toggles button.active { background: #1a2a40; border-color: #7eb8f7; color: #7eb8f7; }

	.feed-row {
		display: flex;
		gap: 12px;
		flex-wrap: wrap;
		margin-top: 12px;
	}
</style>
