open Js_date;

open Js_global;

let getCurrentTime = () => now() |> fromFloat |> toLocaleTimeString;

/* State declaration */
type state = {time: string};

/* Action declaration */
type action =
  | Tick;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Counter");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {time: "Click me"},
  /* State transitions */
  reducer: (action, _state) =>
    switch (action) {
    | Tick =>
      ReasonReact.UpdateWithSideEffects(
        {time: getCurrentTime()},
        (self => ignore(setTimeout(() => self.send(Tick), 1000))),
      )
    },
  render: self => {
    let time = self.state.time;
    <div>
      <button onClick=(_event => self.send(Tick))>
        (ReasonReact.stringToElement(time))
      </button>
    </div>;
  },
};