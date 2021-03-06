open Oni_Core;
open Oni_Model;
open Oni_IntegrationTestLib;

// We'll turn on 'single-file' zen mode, which means when the editor
// is opened with only one file, we'll enter zen mode automatically
let configuration = {|
{ "editor.zenMode.singleFile": true }
|};

let cliOptions =
  Cli.create(
    ~folder=Revery.Environment.getWorkingDirectory(),
    // Specify a single file
    ~filesToOpen=["some-random-file.txt"],
    (),
  );

runTest(
  ~configuration=Some(configuration),
  ~cliOptions=Some(cliOptions),
  ~name="ZenMode: Single-file mode works as expected",
  (_dispatch, wait, _runEffects) => {
    wait(~name="Wait for split to be created 1", (state: State.t) => {
      let splitCount =
        state.windowManager.windowTree |> WindowTree.getSplits |> List.length;
      splitCount == 1;
    });

    // Verify we've entered zen-mode
    wait(~name="We should be in zen-mode", (state: State.t) =>
      state.zenMode == true
    );
  },
);
