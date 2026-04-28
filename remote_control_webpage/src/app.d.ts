// See https://svelte.dev/docs/kit/types#app.d.ts
declare global {
	namespace App {
		// interface Error {}
		// interface Locals {}
		// interface PageData {}
		// interface PageState {}
		// interface Platform {}
	}

	interface RoslibRos {
		on(event: 'connection' | 'error' | 'close', cb: (...args: unknown[]) => void): void;
		close(): void;
	}

	interface RoslibTopic {
		advertise(): void;
		unadvertise(): void;
		publish(msg: object): void;
	}

	interface Window {
		ROSLIB: {
			Ros: new (opts: { url: string }) => RoslibRos;
			Topic: new (opts: { ros: RoslibRos; name: string; messageType: string }) => RoslibTopic;
			Message: new (values: object) => object;
		};
	}
}

export {};
