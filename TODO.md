# TODO

- Modify XnCore such that the window management is handled by a separate executable and the resulting IGame is built as a DLL (project-side).
- Compile-time link the DLL to the XnRunner executable, pass OpenGL context off to game DLL and make current. Call render from game DLL. Game loop is managed by XnRunner.
- Serialize game scene assets (game objects, components, etc) so the editor can parse them, using reflection to modify them in real-time.
- Runtime-link the game DLL to the editor and pass the editor's OpenGL context to it.

Boost.Describe for runtime type reflection.

Factory methods for gameobjects.