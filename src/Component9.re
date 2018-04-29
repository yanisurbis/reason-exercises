type slugifyOption = {. "separator": string};

[@bs.module]
external slugifyWithOptions : (string, slugifyOption) => string =
  "@sindresorhus/slugify";

[@bs.module] external slugify : string => string = "@sindresorhus/slugify";

Js.log(slugify("Batman and Robin"));

Js.log(slugifyWithOptions("Batman and Robin", {"separator": "?"}));

let component = ReasonReact.statelessComponent("Interop");

let make = _children => {
  ...component,
  render: _self =>
    <div> (ReasonReact.stringToElement("Open your console")) </div>,
};