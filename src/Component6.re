type state = {value: string};

type action =
  | Change(string)
  | Reset;

let component = ReasonReact.reducerComponent("SimpleInput");

let make = _children => {
  ...component,
  initialState: () => {value: ""},
  reducer: (action, _state) =>
    switch (action) {
    | Change(newValue) => ReasonReact.Update({value: newValue})
    | Reset => ReasonReact.Update({value: ""})
    },
  render: self => {
    let inputState =
      switch (self.state.value) {
      | "" => "Input is empty"
      | _ => "Inside input: " ++ self.state.value
      };
    let onChange = event =>
      Change(
        ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value,
      )
      |> self.send;
    let onClick = _event => self.send(Reset);
    <div>
      <p> (ReasonReact.stringToElement(inputState)) </p>
      <input value=self.state.value onChange />
      <button onClick> (ReasonReact.stringToElement("Reset")) </button>
    </div>;
  },
};