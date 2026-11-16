# Glossary

**Bridge**: The path that carries an MCP request from the relay through the palette into Vectorworks and back.

**Execution context**: The situation Vectorworks is in when a scripting call runs: who invoked it, whether a command/undo scope is open, and whether a modal dialog is up. Whether a call is safe depends on the call and the context together.

**Inline job**: A script run directly inside the palette's callback, while Vectorworks is in the middle of its own event handling.

**Deferred job**: A script queued from the palette and run a moment later from a run-loop timer, outside the palette callback.

**Native op**: A request the bridge carries out by calling the SDK directly, without going through the Python or VectorScript engine.

**Crasher**: A scripting call that is known to bring Vectorworks down in at least one execution context.

**Sweep**: Running every scripting function through a harness, systematically, to classify how it behaves.

**Safety class**: The single behaviour label a scripting function gets from the sweep, describing the worst thing it does with valid arguments: crasher, hang, interactive, document-level or safe. A function the sweep hasn't reached is unclassified.

**Argument check**: A separate mark on a function whose behaviour gets worse with bad arguments (a modal, a crash or corruption). Its calls are checked against the signature before they run. It can sit alongside any safety class.

**Argument case**: One set of inputs the sweep passes to a function: valid, wrong arity, wrong type or an edge value. Outcomes are recorded per argument case; the safety class is derived from them.

**Class table**: The list of every scripting function with its safety class and argument check, recorded against the Vectorworks build it was swept on. It is the single source the bridge enforces. A local override can sit on top of it.

_Avoid_: blocklist (the old text check covered only a handful of known crashers)

**Unclassified call**: A call to a function with no entry in the class table. It is refused unless the request explicitly allows it.

**Sweep mode**: A state in which the bridge skips its class-table refusals so the sweep can call anything. It is switched on only from the machine itself, never by a request.

**Fixture document**: The throwaway document the sweep runs against. It holds one of each kind of object a function might need a handle to, and it is reset from a clean copy rather than repaired.

**Sweep log**: The append-only record of every sweep job: started before the job is sent, outcome after. A start with no outcome blames that job for a crash or hang.
