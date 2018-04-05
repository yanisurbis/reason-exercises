open Js_date;

open Js_global;

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
};

type action =
  | Start
  | Tick
  | Stop;

let component = ReasonReact.reducerComponent("Counter");

let initialTime: time = {minutes: 0, seconds: 0};

let make = _children => {
  ...component,
  initialState: () => {time: initialTime, timerState: Stopped},
  reducer: (action, state) =>
    switch (action) {
    | Start =>
      ReasonReact.UpdateWithSideEffects(
        {...state, timerState: Ticking},
        (self => ignore(setTimeout(() => self.send(Tick), 1000))),
      )
    | Tick =>
      switch (state.timerState) {
      | Ticking =>
        ReasonReact.UpdateWithSideEffects(
          {...state, time: addSecond(state.time)},
          (self => ignore(setTimeout(() => self.send(Tick), 1000))),
        )
      | Stopped => ReasonReact.Update({...state, time: initialTime})
      }
    | Stop => ReasonReact.Update({time: initialTime, timerState: Stopped})
    },
  render: self => {
    let time = self.state.time;
    let (buttonTitle, action) =
      if (time === initialTime) {
        ("Start", Start);
      } else {
        ("Stop", Stop);
      };
    <div>
      <p> (ReasonReact.stringToElement(timeToString(time))) </p>
      <button onClick=(_event => self.send(action))>
        (ReasonReact.stringToElement(buttonTitle))
      </button>
    </div>;
  },
};