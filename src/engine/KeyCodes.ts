/**
 * Key codes matching the original Grim2D/DirectInput key mapping
 *
 * These map to common keyboard keys used in the game.
 * The original used DirectInput scan codes.
 */
export enum KeyCode {
    // Letters
    A = 65,
    B = 66,
    C = 67,
    D = 68,
    E = 69,
    F = 70,
    G = 71,
    H = 72,
    I = 73,
    J = 74,
    K = 75,
    L = 76,
    M = 77,
    N = 78,
    O = 79,
    P = 80,
    Q = 81,
    R = 82,
    S = 83,
    T = 84,
    U = 85,
    V = 86,
    W = 87,
    X = 88,
    Y = 89,
    Z = 90,

    // Numbers
    Digit0 = 48,
    Digit1 = 49,
    Digit2 = 50,
    Digit3 = 51,
    Digit4 = 52,
    Digit5 = 53,
    Digit6 = 54,
    Digit7 = 55,
    Digit8 = 56,
    Digit9 = 57,

    // Function keys
    F1 = 112,
    F2 = 113,
    F3 = 114,
    F4 = 115,
    F5 = 116,
    F6 = 117,
    F7 = 118,
    F8 = 119,
    F9 = 120,
    F10 = 121,
    F11 = 122,
    F12 = 123,

    // Special keys
    Escape = 27,
    Space = 32,
    Enter = 13,
    Backspace = 8,
    Tab = 9,
    Shift = 16,
    Control = 17,
    Alt = 18,

    // Arrow keys
    Left = 37,
    Up = 38,
    Right = 39,
    Down = 40,

    // Navigation keys
    PageUp = 33,
    PageDown = 34,

    // Other
    Backquote = 192, // Tilde/console key
    Minus = 189,
    Equal = 187,
    BracketLeft = 219,
    BracketRight = 221,
    Semicolon = 186,
    Quote = 222,
    Backslash = 220,
    Comma = 188,
    Period = 190,
    Slash = 191,
}

/**
 * Mouse button codes
 */
export enum MouseButton {
    Left = 0,
    Middle = 1,
    Right = 2,
}

/**
 * Map browser key codes to our KeyCode enum
 */
export function keyCodeFromEvent(event: KeyboardEvent): number {
    return event.keyCode;
}
