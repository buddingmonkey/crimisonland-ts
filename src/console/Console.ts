/**
 * Console - Command-line console system
 *
 * Port of the console system from crimsonland.exe_decompiled.c (lines 7-800+)
 * Provides command parsing, cvar system, and logging.
 */

export type CommandHandler = (args: string[]) => void;

/**
 * Console variable with string value and optional numeric representation
 */
export interface CVar {
    name: string;
    value: string;
    numericValue: number;
}

/**
 * Console command registration
 */
interface Command {
    name: string;
    handler: CommandHandler;
}

/**
 * Console log entry
 */
interface LogEntry {
    text: string;
    timestamp: number;
}

/**
 * Console - Game console system
 *
 * Implements:
 * - console_init (line 444) -> constructor
 * - console_input_clear (line 7) -> clearInput()
 * - console_input_poll (line 34) -> pollInput()
 * - console_tokenize_line -> tokenize()
 * - console_exec_line (line 736) -> execute()
 * - console_register_command (line 482) -> registerCommand()
 * - console_register_cvar (line 476) -> registerCvar() / setCvar()
 */
export class Console {
    // Commands and cvars
    private commands: Map<string, Command> = new Map();
    private cvars: Map<string, CVar> = new Map();

    // Log history
    private log: LogEntry[] = [];
    private maxLogEntries: number = 4096; // 0x1000 in original

    // Input state
    private inputBuffer: string = '';
    private inputReady: boolean = false;
    private inputEnabled: boolean = false;

    // Console visibility
    private isOpen: boolean = false;
    private height: number = 370; // Increased from 300 to show more log lines

    // Scroll state
    private scrollOffset: number = 0; // Lines scrolled back from bottom (0 = at bottom)

    // History
    private history: string[] = [];
    private historyIndex: number = 0;
    private maxHistory: number = 100;

    // Echo setting
    private echoEnabled: boolean = true;

    constructor() {
        this.registerBuiltinCommands();
    }

    /**
     * Register built-in console commands
     * Maps to console_init registrations (lines 482-490)
     */
    private registerBuiltinCommands(): void {
        this.registerCommand('cmdlist', () => {
            const names = Array.from(this.commands.keys()).sort();
            names.forEach((name) => this.print(name));
            this.print(`${names.length} commands`);
        });

        this.registerCommand('vars', () => {
            const names = Array.from(this.cvars.keys()).sort();
            names.forEach((name) => this.print(name));
            this.print(`${names.length} variables`);
        });

        this.registerCommand('echo', (args) => {
            if (args.length === 1) {
                if (args[0] === 'off') {
                    this.echoEnabled = false;
                    return;
                } else if (args[0] === 'on') {
                    this.echoEnabled = true;
                    return;
                }
            }
            this.print(args.join(' '));
        });

        this.registerCommand('set', (args) => {
            if (args.length !== 2) {
                this.print('set <var> <value>');
                return;
            }
            this.setCvar(args[0], args[1]);
            const cvar = this.getCvar(args[0]);
            if (cvar) {
                this.print(`"${cvar.name}" set to "${cvar.value}"`);
            }
        });

        this.registerCommand('clear', () => {
            this.clearLog();
        });

        this.registerCommand('quit', () => {
            // In browser context, we can't really quit
            this.print('Cannot quit in browser context');
        });

        this.registerCommand('help', () => {
            this.print('Available commands:');
            this.print('  cmdlist - list all commands');
            this.print('  vars - list all variables');
            this.print('  set <var> <value> - set a variable');
            this.print('  echo <text> - print text');
            this.print('  clear - clear console log');
            this.print('  help - show this help');
        });
    }

    // ============================================
    // Command registration
    // ============================================

    /**
     * Register a console command
     * Maps to console_register_command (line 482)
     */
    registerCommand(name: string, handler: CommandHandler): void {
        this.commands.set(name.toLowerCase(), { name, handler });
    }

    /**
     * Find a registered command
     */
    findCommand(name: string): Command | undefined {
        return this.commands.get(name.toLowerCase());
    }

    // ============================================
    // CVar system
    // ============================================

    /**
     * Register or update a cvar
     * Maps to console_register_cvar (line 476)
     */
    setCvar(name: string, value: string): void {
        const numericValue = parseFloat(value) || 0;
        this.cvars.set(name.toLowerCase(), {
            name,
            value,
            numericValue,
        });
    }

    /**
     * Get a cvar by name
     */
    getCvar(name: string): CVar | undefined {
        return this.cvars.get(name.toLowerCase());
    }

    /**
     * Get cvar value as string
     */
    getCvarString(name: string, defaultValue: string = ''): string {
        return this.getCvar(name)?.value ?? defaultValue;
    }

    /**
     * Get cvar value as number
     */
    getCvarNumber(name: string, defaultValue: number = 0): number {
        return this.getCvar(name)?.numericValue ?? defaultValue;
    }

    // ============================================
    // Tokenization and execution
    // ============================================

    /**
     * Tokenize a command line into arguments
     * Maps to console_tokenize_line
     */
    tokenize(line: string): string[] {
        const tokens: string[] = [];
        let current = '';
        let inQuotes = false;

        for (let i = 0; i < line.length; i++) {
            const char = line[i];

            if (char === '"') {
                inQuotes = !inQuotes;
            } else if (char === ' ' && !inQuotes) {
                if (current.length > 0) {
                    tokens.push(current);
                    current = '';
                }
            } else {
                current += char;
            }
        }

        if (current.length > 0) {
            tokens.push(current);
        }

        return tokens;
    }

    /**
     * Execute a console command line
     * Maps to console_exec_line (line 736)
     */
    execute(line: string): void {
        const tokens = this.tokenize(line.trim());
        if (tokens.length === 0) return;

        const commandName = tokens[0].toLowerCase();
        const args = tokens.slice(1);

        // Check for cvar first
        const cvar = this.getCvar(commandName);
        if (cvar) {
            if (args.length === 1) {
                // Set cvar value
                this.setCvar(commandName, args[0]);
                if (this.echoEnabled) {
                    this.print(`"${commandName}" set to "${args[0]}" (${parseFloat(args[0]) || 0})`);
                }
            } else if (this.echoEnabled) {
                // Display current value
                this.print(`"${commandName}" is "${cvar.value}" (${cvar.numericValue})`);
            }
            return;
        }

        // Check for command
        const command = this.findCommand(commandName);
        if (command) {
            try {
                command.handler(args);
            } catch (error) {
                this.print(`Error executing command: ${error}`);
            }
            return;
        }

        // Unknown command
        this.print(`Unknown command: ${commandName}`);
    }

    // ============================================
    // Input handling
    // ============================================

    /**
     * Clear input buffer
     * Maps to console_input_clear (line 7)
     */
    clearInput(): void {
        this.inputBuffer = '';
        this.inputReady = false;
    }

    /**
     * Get current input buffer
     * Maps to console_input_buffer (line 22)
     */
    getInputBuffer(): string {
        return this.inputBuffer;
    }

    /**
     * Process a character input
     * Maps to console_input_poll (line 34)
     */
    processChar(charCode: number): void {
        if (!this.inputEnabled) return;

        // Ignore backtick (96) - it's used to toggle console
        if (charCode === 96) return;

        if (charCode === 13) {
            // Enter
            this.inputReady = true;
        } else if (charCode === 8) {
            // Backspace
            if (this.inputBuffer.length > 0) {
                this.inputBuffer = this.inputBuffer.slice(0, -1);
            }
        } else if (charCode >= 32 && charCode < 127) {
            // Printable ASCII
            if (this.inputBuffer.length < 1023) {
                // 0x3ff limit from original
                this.inputBuffer += String.fromCharCode(charCode);
            }
        }
    }

    /**
     * Check if input is ready (Enter was pressed)
     */
    isInputReady(): boolean {
        return this.inputReady;
    }

    /**
     * Submit current input and execute
     */
    submitInput(): void {
        if (this.inputBuffer.length > 0) {
            // Add to history
            if (this.history.length === 0 || this.history[0] !== this.inputBuffer) {
                this.history.unshift(this.inputBuffer);
                if (this.history.length > this.maxHistory) {
                    this.history.pop();
                }
            }
            this.historyIndex = 0;

            // Echo and execute
            this.print(`> ${this.inputBuffer}`);
            this.execute(this.inputBuffer);
        }
        this.clearInput();
    }

    /**
     * Navigate history (up = -1, down = 1)
     */
    navigateHistory(direction: number): void {
        if (this.history.length === 0) return;

        this.historyIndex = Math.max(0, Math.min(this.history.length - 1, this.historyIndex + direction));
        this.inputBuffer = this.history[this.historyIndex] || '';
    }

    // ============================================
    // Logging
    // ============================================

    /**
     * Print a line to the console log
     * Maps to console_printf (line 630)
     */
    print(text: string): void {
        // Enforce log limit
        if (this.log.length >= this.maxLogEntries) {
            this.log.shift();
            // Adjust scroll offset since we removed an entry from the top
            if (this.scrollOffset > 0) {
                this.scrollOffset = Math.max(0, this.scrollOffset - 1);
            }
        }

        this.log.push({
            text,
            timestamp: Date.now(),
        });

        // Also log to browser console for debugging
        console.log(`[Console] ${text}`);
    }

    /**
     * Clear the console log
     * Maps to console_clear_log (line 154)
     */
    clearLog(): void {
        this.log = [];
    }

    /**
     * Get log entries
     */
    getLog(): LogEntry[] {
        return this.log;
    }

    /**
     * Get recent log entries
     */
    getRecentLog(count: number): LogEntry[] {
        return this.log.slice(-count);
    }

    /**
     * Get visible log entries based on current scroll offset
     * @param visibleLines Number of lines visible in the console window
     */
    getVisibleLog(visibleLines: number): LogEntry[] {
        const totalEntries = this.log.length;
        if (totalEntries === 0) return [];

        // Calculate the end index (exclusive) — how far back from the end we are
        const endIndex = totalEntries - this.scrollOffset;
        const startIndex = Math.max(0, endIndex - visibleLines);

        return this.log.slice(startIndex, Math.max(0, endIndex));
    }

    // ============================================
    // Scrolling
    // ============================================

    /**
     * Scroll up (back through history)
     * @param lines Number of lines to scroll
     */
    scrollUp(lines: number): void {
        const maxOffset = Math.max(0, this.log.length - 1);
        this.scrollOffset = Math.min(maxOffset, this.scrollOffset + lines);
    }

    /**
     * Scroll down (toward present)
     * @param lines Number of lines to scroll
     */
    scrollDown(lines: number): void {
        this.scrollOffset = Math.max(0, this.scrollOffset - lines);
    }

    /**
     * Scroll to the bottom (latest output)
     */
    scrollToBottom(): void {
        this.scrollOffset = 0;
    }

    /**
     * Get current scroll offset
     */
    getScrollOffset(): number {
        return this.scrollOffset;
    }

    /**
     * Check if console is scrolled to the bottom
     */
    isScrolledToBottom(): boolean {
        return this.scrollOffset === 0;
    }

    // ============================================
    // Console visibility
    // ============================================

    /**
     * Set console open state
     * Maps to console_set_open (line 650)
     */
    setOpen(open: boolean): void {
        this.isOpen = open;
        this.inputEnabled = open;
        if (open) {
            this.clearInput();
        }
    }

    /**
     * Toggle console visibility
     */
    toggle(): void {
        this.setOpen(!this.isOpen);
    }

    /**
     * Check if console is open
     */
    getIsOpen(): boolean {
        return this.isOpen;
    }

    /**
     * Get console height
     */
    getHeight(): number {
        return this.height;
    }

    /**
     * Set console height
     */
    setHeight(height: number): void {
        this.height = height;
    }
}

// Singleton instance
export const gameConsole = new Console();
