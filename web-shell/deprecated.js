import { Terminal } from "xterm";
import { fit } from 'xterm/lib/addons/fit/fit'
import { winptyCompatInit } from 'xterm/lib/addons/winptyCompat/winptyCompat';

function setupTerminal(Module) {
	const conatiner = document.getElementById('container');
	conatiner.innerHTML = '';

	const terminal = new Terminal({
		fontFamily: 'monospace',
		lineHeight: 1.4,
		cursorBlink: true,
		scrollback: 1000,
		tabStopWidth: 4,
	});

	let resizedFinished = null;
	window.addEventListener('resize', () => {
		clearTimeout(resizedFinished)
		resizedFinished = setTimeout(() => {
			fit(terminal);
		}, 250)
	})

	terminal.open(conatiner);
	winptyCompatInit(terminal);
	fit(terminal);
	showPrompt();

	terminal.on('key', (key, ev) => {
		//@ts-ignore
		const isPrintable = (!ev.altKey && !ev.altGraphKey && !ev.ctrlKey && !ev.metaKey);

		if (ev.keyCode == 13) {
			showPrompt();
		} else if (ev.keyCode == 8) {
			// Do not delete the prompt
			debugger;
			// if (terminal.x > 2) {
			terminal.write('\b \b');
			// }
		} else if (isPrintable) {
			terminal.write(key);
		}
	});

	function showPrompt() {
		terminal.write('\r\n$ ');
	}
}
