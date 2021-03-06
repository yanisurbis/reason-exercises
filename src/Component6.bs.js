// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.reducerComponent("SimpleInput");

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (self) {
      var match = self[/* state */2][/* value */0];
      var inputState = match === "" ? "Input is empty" : "Inside input: " + self[/* state */2][/* value */0];
      var onChange = function ($$event) {
        return Curry._1(self[/* send */4], /* Change */[$$event.target.value]);
      };
      var onClick = function () {
        return Curry._1(self[/* send */4], /* Reset */0);
      };
      return React.createElement("div", undefined, React.createElement("p", undefined, inputState), React.createElement("input", {
                      value: self[/* state */2][/* value */0],
                      onChange: onChange
                    }), React.createElement("button", {
                      onClick: onClick
                    }, "Reset"));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[/* value */""];
    });
  newrecord[/* reducer */12] = (function (action, _) {
      if (action) {
        return /* Update */Block.__(0, [/* record */[/* value */action[0]]]);
      } else {
        return /* Update */Block.__(0, [/* record */[/* value */""]]);
      }
    });
  return newrecord;
}

exports.component = component;
exports.make = make;
/* component Not a pure module */
