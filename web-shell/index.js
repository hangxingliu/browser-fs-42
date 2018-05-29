//@ts-check
/// <reference path="./types.d.ts" />

import _ from 'lodash';
import $ from "jquery";
import initJQueryTerminal from "jquery.terminal";
initJQueryTerminal($);

const RETURN_CALLBACK = p => p;

document.addEventListener('DOMContentLoaded', main);

function main() {
	const onWindowResize = _.debounce(_onWindowResize, 200);
	const terminalOptions = {
		greetings: 'Browser FileSystem 42',
		prompt: getPrompt
	};
	const terminal = $('#container').terminal(command => {
		Module.fs_repl(command);
	}, terminalOptions);

	onWindowResize();
	window.addEventListener('resize', onWindowResize);

	const webAssmeblyScript = document.createElement('script');
	window['Module'] = {};
	Module.print = content => terminal.echo(getEchoString(content));
	Module.printErr = content => terminal.echo(`[[;red;]${getEchoString(content)}]`);
	Module.onRuntimeInitialized = () => {
		console.log('WebAssmebly module be loaded!');
		Module.fs_init(16 * 1024); // 16KB
		terminal.set_prompt(getPrompt);
	}
	webAssmeblyScript.src = 'browser-fs-42-wasm.js';
	document.head.appendChild(webAssmeblyScript);


	function getPrompt(callback = RETURN_CALLBACK) {
		const getPwd = _.get(window, 'Module.fs_pwd')
		if (!getPwd) return callback('$ ');
		return callback(`[[b;green;]${getEchoString(getPwd())}] $ `);
	}
	/** @param {string} str */
	function getEchoString(str) { return str.replace(/\]/g, '&#93'); }
	function _onWindowResize() {
		terminal.resize(window.innerWidth - 20, window.innerHeight - 20);
	}
}



