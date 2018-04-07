let component = ReasonReact.statelessComponent("Item");

type item = {
  id: int,
  completed: bool,
  description: string,
};

let make = (~item: item, ~onDelete, ~onToggleComplete, _children) => {
  ...component,
  render: _self => {
    let {completed, description} = item;
    let textStyle =
      item.completed ?
        ReactDOMRe.Style.make(~textDecoration="line-through", ()) :
        ReactDOMRe.Style.make();
    <div>
      <input
        _type="checkbox"
        checked=(Js.Boolean.to_js_boolean(completed))
        onChange=onToggleComplete
      />
      <span style=textStyle>
        (ReasonReact.stringToElement(description))
      </span>
      <button
        onClick=onDelete style=(ReactDOMRe.Style.make(~margin="0.5rem", ()))>
        (ReasonReact.stringToElement("Delete"))
      </button>
    </div>;
  },
};