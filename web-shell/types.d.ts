// WebAssembly export context
declare var Module: any;

type JQueryTerminal = {
	echo: (ctx?: string | Function, options?: any);
	[x: string]: any;
};

interface JQuery<HTMLElement> {
	terminal: (...params) => JQueryTerminal;
};
