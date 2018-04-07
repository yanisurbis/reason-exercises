
type item = Component7Item.item;

type view =
  | All
  | Completed
  | NotCompleted;

type state = {
  list: list(item),
  view,
  value: string,
  nextItemId: int,
};

type action =
  | Add
  | ToggleComplete(item)
  | Delete(item)
  | ChangeView(view)
  | ChangeValue(string);

let component = ReasonReact.reducerComponent("SimpleToDoList");

let marginHalfRem = ReactDOMRe.Style.make(~margin="0.5rem", ());

let make = _children => {
  ...component,
  initialState: () => {list: [], view: All, value: "", nextItemId: 0},
  reducer: (action, state) => {
    let list = state.list;
    switch (action) {
    | Add =>
      ReasonReact.Update({...state, list: List.append(list, [{
        id: state.nextItemId,
        description: state.value,
        completed: false,
      }]), nextItemId: state.nextItemId + 1, value: ""});
    | ToggleComplete(completedItem) =>
      let updatedList =
        List.map(
          (item:item) =>
            if (item.id === completedItem.id) {
              {...item, completed: !completedItem.completed};
            } else {
              item;
            },
          list,
        );
      ReasonReact.Update({...state, list: updatedList});
    | Delete(deletedItem) =>
      let updatedList =
        List.filter(
          (item:item) =>
            if (item.id !== deletedItem.id) {
              true;
            } else {
              false;
            },
          list,
        );
      ReasonReact.Update({...state, list: updatedList});
    | ChangeView(view) => 
      ReasonReact.Update({...state, view});
    | ChangeValue(value) =>
      ReasonReact.Update({...state, value});
    };
  },
  render: self => {
    let onChange = event => {
      let value = ReactDOMRe.domElementToObj(ReactEventRe.Form.target(event))##value;
      self.send(ChangeValue(value));
    };

    let onSubmit = event => {
      ReactEventRe.Synthetic.preventDefault(event);
      self.send(Add);
    };

    let onShowAll = _event => self.send(ChangeView(All));
    let onShowCompletedOnly = _event => self.send(ChangeView(Completed));
    let onShowNotCompletedOnly = _event => self.send(ChangeView(NotCompleted));

    let filterFunc = switch(self.state.view) {
    | All => (_i) => true
    | Completed => (i:item) => i.completed
    | NotCompleted => (i:item) => !i.completed
    };

    let items =
          self.state.list
          |> List.filter(filterFunc)
          |> List.map(
             (item:item) => {
               <Component7Item
                 key={string_of_int(item.id)}
                 item
                 onDelete=(_event => self.send(Delete(item)))
                 onToggleComplete=(_event => self.send(ToggleComplete(item)))
               />;
             }
           );

    <div>
      (ReasonReact.arrayToElement(Array.of_list(items)))
      <form onSubmit style=marginHalfRem>
        <input value=self.state.value onChange />
        <button> (ReasonReact.stringToElement("Add")) </button>
      </form>
      <button onClick=onShowAll style=marginHalfRem> (ReasonReact.stringToElement("Show All")) </button>
      <button onClick=onShowCompletedOnly style=marginHalfRem> (ReasonReact.stringToElement("Show Completed Only")) </button>
      <button onClick=onShowNotCompletedOnly style=marginHalfRem> (ReasonReact.stringToElement("Show Not Completed Only")) </button>
    </div>;
  },
};