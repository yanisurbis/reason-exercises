open Js.Global;

type time = {
  minutes: int,
  seconds: int,
};

let addSecond = ({minutes, seconds}: time) =>
  if (seconds < 60) {
    {minutes, seconds: seconds + 1};
  } else {
    {minutes: minutes + 1, seconds: 0};
  };

let timeToString = ({minutes, seconds}) =>
  string_of_int(minutes)
  ++ " minutes, "
  ++ string_of_int(seconds)
  ++ " seconds!";

type timerState =
  | Ticking
  | Stopped;

type state = {
  time,
  timerState,
  intervalId: ref(option(intervalId)),
};

type actionWhileTicking = unit => unit;

type action =
  | StartTicking(actionWhileTicking)
  | Tick
  | Stop;

let component = ReasonReact.reducerComponent("Counter");

let initialTime: time = {minutes: 0, seconds: 0};

let make = _children => {
  ...component,
  initialState: () => {
    time: initialTime,
    timerState: Stopped,
    intervalId: ref(None),
  },
  reducer: (action, state) =>
    switch (action) {
    | StartTicking(actionWhileTicking) =>
      state.intervalId :=
        Some(Js.Global.setInterval(actionWhileTicking, 1000));
      ReasonReact.Update({...state, timerState: Ticking});
    | Tick => ReasonReact.Update({...state, time: addSecond(state.time)})
    | Stop =>
      switch (state.intervalId^) {
      | Some(intervalId) =>
        Js.Global.clearInterval(intervalId);
        state.intervalId := None;
      | None => ()
      };
      ReasonReact.Update({...state, time: initialTime, timerState: Stopped});
    },
  render: self => {
    let timerState = self.state.timerState;
    let time = self.state.time;
    let actionWhileTicking: actionWhileTicking = () => self.send(Tick);
    let (buttonTitle, action) =
      switch (timerState) {
      | Stopped => ("Start", StartTicking(actionWhileTicking))
      | Ticking => ("Stop", Stop)
      };
    <div>
      <p> (ReasonReact.stringToElement(timeToString(time))) </p>
      <button onClick=(_event => self.send(action))>
        (ReasonReact.stringToElement(buttonTitle))
      </button>
    </div>;
  },
};