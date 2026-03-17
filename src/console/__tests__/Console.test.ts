/**
 * Console unit tests
 */

import { describe, it, expect, beforeEach, vi } from 'vitest';
import { Console } from '../Console';

describe('Console', () => {
    let console: Console;

    beforeEach(() => {
        console = new Console();
    });

    describe('tokenize', () => {
        it('should split simple command', () => {
            const result = console.tokenize('echo hello');
            expect(result).toEqual(['echo', 'hello']);
        });

        it('should handle multiple arguments', () => {
            const result = console.tokenize('set foo bar');
            expect(result).toEqual(['set', 'foo', 'bar']);
        });

        it('should handle quoted strings', () => {
            const result = console.tokenize('echo "hello world"');
            expect(result).toEqual(['echo', 'hello world']);
        });

        it('should handle empty string', () => {
            const result = console.tokenize('');
            expect(result).toEqual([]);
        });

        it('should handle multiple spaces', () => {
            const result = console.tokenize('echo   hello   world');
            expect(result).toEqual(['echo', 'hello', 'world']);
        });

        it('should handle single word', () => {
            const result = console.tokenize('cmdlist');
            expect(result).toEqual(['cmdlist']);
        });
    });

    describe('registerCommand', () => {
        it('should register and find command', () => {
            const handler = vi.fn();
            console.registerCommand('test', handler);

            const cmd = console.findCommand('test');
            expect(cmd).toBeDefined();
            expect(cmd?.name).toBe('test');
        });

        it('should be case-insensitive', () => {
            const handler = vi.fn();
            console.registerCommand('TEST', handler);

            const cmd = console.findCommand('test');
            expect(cmd).toBeDefined();
        });
    });

    describe('execute', () => {
        it('should execute registered command', () => {
            const handler = vi.fn();
            console.registerCommand('test', handler);

            console.execute('test arg1 arg2');

            expect(handler).toHaveBeenCalledWith(['arg1', 'arg2']);
        });

        it('should handle unknown command', () => {
            // Should not throw
            expect(() => console.execute('unknowncommand')).not.toThrow();
        });

        it('should execute built-in cmdlist', () => {
            // Should not throw
            expect(() => console.execute('cmdlist')).not.toThrow();
        });
    });

    describe('cvars', () => {
        it('should set and get cvar', () => {
            console.setCvar('test_var', 'hello');

            const cvar = console.getCvar('test_var');
            expect(cvar?.value).toBe('hello');
        });

        it('should parse numeric value', () => {
            console.setCvar('test_num', '42.5');

            const cvar = console.getCvar('test_num');
            expect(cvar?.numericValue).toBe(42.5);
        });

        it('should return default for missing cvar', () => {
            expect(console.getCvarString('missing', 'default')).toBe('default');
            expect(console.getCvarNumber('missing', 123)).toBe(123);
        });

        it('should be case-insensitive', () => {
            console.setCvar('TEST_VAR', 'value');

            expect(console.getCvar('test_var')?.value).toBe('value');
        });
    });

    describe('input handling', () => {
        it('should clear input', () => {
            console.setOpen(true);
            console.processChar(65); // 'A'
            console.processChar(66); // 'B'
            expect(console.getInputBuffer()).toBe('AB');

            console.clearInput();
            expect(console.getInputBuffer()).toBe('');
        });

        it('should process printable characters', () => {
            console.setOpen(true);
            console.processChar(72); // 'H'
            console.processChar(105); // 'i'

            expect(console.getInputBuffer()).toBe('Hi');
        });

        it('should handle backspace', () => {
            console.setOpen(true);
            console.processChar(72); // 'H'
            console.processChar(105); // 'i'
            console.processChar(8); // Backspace

            expect(console.getInputBuffer()).toBe('H');
        });

        it('should set input ready on enter', () => {
            console.setOpen(true);
            console.processChar(72); // 'H'
            console.processChar(13); // Enter

            expect(console.isInputReady()).toBe(true);
        });
    });

    describe('logging', () => {
        it('should add log entries', () => {
            console.print('test message');

            const log = console.getLog();
            expect(log.length).toBeGreaterThan(0);
            expect(log[log.length - 1].text).toBe('test message');
        });

        it('should clear log', () => {
            console.print('message 1');
            console.print('message 2');
            console.clearLog();

            expect(console.getLog()).toHaveLength(0);
        });

        it('should get recent log entries', () => {
            for (let i = 0; i < 10; i++) {
                console.print(`message ${i}`);
            }

            const recent = console.getRecentLog(3);
            expect(recent).toHaveLength(3);
            expect(recent[2].text).toBe('message 9');
        });
    });

    describe('visibility', () => {
        it('should toggle open state', () => {
            expect(console.getIsOpen()).toBe(false);

            console.toggle();
            expect(console.getIsOpen()).toBe(true);

            console.toggle();
            expect(console.getIsOpen()).toBe(false);
        });

        it('should set open state directly', () => {
            console.setOpen(true);
            expect(console.getIsOpen()).toBe(true);

            console.setOpen(false);
            expect(console.getIsOpen()).toBe(false);
        });
    });

    describe('scrolling', () => {
        it('should have default scroll offset of 0', () => {
            expect(console.getScrollOffset()).toBe(0);
            expect(console.isScrolledToBottom()).toBe(true);
        });

        it('should scroll up and increase offset', () => {
            for (let i = 0; i < 30; i++) {
                console.print(`message ${i}`);
            }

            console.scrollUp(5);
            expect(console.getScrollOffset()).toBe(5);
            expect(console.isScrolledToBottom()).toBe(false);
        });

        it('should clamp scroll up to max log length', () => {
            for (let i = 0; i < 10; i++) {
                console.print(`message ${i}`);
            }

            console.scrollUp(100); // Way more than log size
            expect(console.getScrollOffset()).toBe(9); // max is log.length - 1
        });

        it('should scroll down and decrease offset', () => {
            for (let i = 0; i < 30; i++) {
                console.print(`message ${i}`);
            }

            console.scrollUp(10);
            expect(console.getScrollOffset()).toBe(10);

            console.scrollDown(3);
            expect(console.getScrollOffset()).toBe(7);
        });

        it('should clamp scroll down to 0', () => {
            for (let i = 0; i < 10; i++) {
                console.print(`message ${i}`);
            }

            console.scrollUp(5);
            console.scrollDown(100); // Way more than offset
            expect(console.getScrollOffset()).toBe(0);
            expect(console.isScrolledToBottom()).toBe(true);
        });

        it('should scroll to bottom', () => {
            for (let i = 0; i < 20; i++) {
                console.print(`message ${i}`);
            }

            console.scrollUp(10);
            expect(console.getScrollOffset()).toBe(10);

            console.scrollToBottom();
            expect(console.getScrollOffset()).toBe(0);
            expect(console.isScrolledToBottom()).toBe(true);
        });

        it('should return correct visible log at bottom', () => {
            for (let i = 0; i < 30; i++) {
                console.print(`message ${i}`);
            }

            const visible = console.getVisibleLog(5);
            expect(visible).toHaveLength(5);
            expect(visible[4].text).toBe('message 29');
            expect(visible[0].text).toBe('message 25');
        });

        it('should return correct visible log when scrolled up', () => {
            for (let i = 0; i < 30; i++) {
                console.print(`message ${i}`);
            }

            console.scrollUp(10);
            const visible = console.getVisibleLog(5);
            expect(visible).toHaveLength(5);
            expect(visible[4].text).toBe('message 19'); // 30 - 10 - 1 = 19
            expect(visible[0].text).toBe('message 15');
        });

        it('should return empty array for empty log', () => {
            const visible = console.getVisibleLog(5);
            expect(visible).toHaveLength(0);
        });

        it('should preserve scroll offset when new text is printed while scrolled up', () => {
            for (let i = 0; i < 20; i++) {
                console.print(`message ${i}`);
            }

            console.scrollUp(5);
            expect(console.getScrollOffset()).toBe(5);

            // Printing new text should NOT reset scroll offset
            console.print('new message');
            expect(console.getScrollOffset()).toBe(5);
        });
    });
});
