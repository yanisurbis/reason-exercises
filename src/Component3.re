/* State declaration */
type state = {count: int};

/* Action declaration */
type action =
  | Increment
  | Decrement;

/* Component template declaration.
   Needs to be **after** state and action declarations! */
let component = ReasonReact.reducerComponent("Counter");

/* greeting and children are props. `children` isn't used, therefore ignored.
   We ignore it by prepending it with an underscore */
let make = _children => {
  /* spread the other default fields of component here and override a few */
  ...component,
  initialState: () => {count: 0},
  /* State transitions */
  reducer: (action, state) =>
    switch (action) {
    | Increment => ReasonReact.Update({count: state.count + 1})
    | Decrement => ReasonReact.Update({count: state.count - 1})
    },
  render: self => {
    let counter = string_of_int(self.state.count);
    <div>
      <button onClick=(_event => self.send(Decrement))>
        (ReasonReact.stringToElement("Decrement"))
      </button>
      <b> (ReasonReact.stringToElement(counter)) </b>
      <button onClick=(_event => self.send(Increment))>
        (ReasonReact.stringToElement("Increment"))
      </button>
    </div>;
  },
};