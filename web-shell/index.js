//@ts-check
/// <reference path="./types.d.ts" />

import _ from 'lodash';
import $ from "jquery";
import initJQueryTerminal from "jquery.terminal";
import * as cowsay from "cowsay";
import hexy from "./hexy";

initJQueryTerminal($);

const RETURN_CALLBACK = p => p;

document.addEventListener('DOMContentLoaded', main);

function main() {
	const onWindowResize = _.debounce(_onWindowResize, 200);
	const terminalOptions = {
		greetings: 'Browser FileSystem 42',
		prompt: getPrompt
	};
	const terminal = $('#container').terminal(handlerCommand, terminalOptions);

	onWindowResize();
	window.addEventListener('resize', onWindowResize);

	const webAssmeblyScript = document.createElement('script');
	window['Module'] = {};
	// initial: 1000 * 64Kib: 64 Mib
	// maximum: 5000 * 64Kib: 320 Mib
	//@ts-ignore
	Module.wasmMemory = new WebAssembly.Memory({ initial: 1000, maximum: 5000 }); // more memory
	Module.print = onStdout;
	Module.printErr = onStderr;
	Module.onRuntimeInitialized = () => {
		console.log('WebAssmebly module be loaded!');

		Module.fs_init(32 * 1024 * 1024); // 32MB
		terminal.set_prompt(getPrompt);
		handlerCommand('cowsay filesystem initialized!');
	}
	webAssmeblyScript.src = 'browser-fs-42-wasm.js';
	document.head.appendChild(webAssmeblyScript);


	/** @param {string} command */
	function handlerCommand(command) {
		const commandName = (command.match(/^[\w\-]+/) || [''])[0];
		if (commandName == 'for') {
			const mtx = command.match(/^for\s+(\d+)\s+(.+)$/);
			if (!mtx)
				return onStderr('Example: for 100 echo hello ${i}');
			const count = parseInt(mtx[1], 10);
			const tmpl = mtx[2];
			if (isNaN(count))
				return onStderr(`Error: "${mtx[1]}" is not a integer!`);
			for (let i = 0; i < count; i++)
				handlerCommand(tmpl.replace(/\$\{\s*i\s*\}/g, i.toString(10)));
			return onStdout(`Success: execute ${count} commands!`);
		}
		if (commandName == 'echo')
			return onStdout(command.match(/^echo\s+(.+)$/)[1]);
		if (commandName == 'cowsay')
			return onStdout(cowsay.say({ text: command.match(/^cowsay\s+(.+)$/)[1] }));
		if (commandName == 'zoom')
			return void $('body').toggleClass('zoom');
		if (commandName == 'disk')
			return void lowLevelDeviceDump(command);
		Module.fs_repl(command);
	}
	/** @param {string} command */
	function lowLevelDeviceDump(command) {
		const mtx = command.match(/^disk\s+(\d+)(\s+\d+)?$/);
		if (!mtx)
			return onStderr('Example: disk $offset $size');
		const offset = parseInt(mtx[1]) || 0;
		const size = parseInt(mtx[2] || '16') || 0;
		const disk = Module.fs_access_device(offset, size);
		console.log(disk)
		onStdout(hexy(disk));
	}
	function getPrompt(callback = RETURN_CALLBACK) {
		const getPwd = _.get(window, 'Module.fs_pwd')
		if (!getPwd) return callback('$ ');
		return callback(`[[b;green;]${getEchoString(getPwd())}] $ `);
	}
	/** @param {string} str */
	function getEchoString(str) { return str.replace(/\]/g, '&#93'); }
	function onStdout(content) { terminal.echo(getEchoString(content)); }
	function onStderr(content) { terminal.echo(`[[;red;]${getEchoString(content)}]`); }
	function _onWindowResize() {
		terminal.resize(window.innerWidth - 20, window.innerHeight - 20);
	}
}



