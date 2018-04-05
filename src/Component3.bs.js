// Generated by BUCKLESCRIPT VERSION 2.2.3, PLEASE EDIT WITH CARE
'use strict';

var Block = require("bs-platform/lib/js/block.js");
var Curry = require("bs-platform/lib/js/curry.js");
var React = require("react");
var ReasonReact = require("reason-react/src/ReasonReact.js");

var component = ReasonReact.reducerComponent("Counter");

function make() {
  var newrecord = component.slice();
  newrecord[/* render */9] = (function (self) {
      var counter = String(self[/* state */2][/* count */0]);
      return React.createElement("div", undefined, React.createElement("button", {
                      onClick: (function () {
                          return Curry._1(self[/* send */4], /* Decrement */1);
                        })
                    }, "Decrement"), React.createElement("b", undefined, counter), React.createElement("button", {
                      onClick: (function () {
                          return Curry._1(self[/* send */4], /* Increment */0);
                        })
                    }, "Increment"));
    });
  newrecord[/* initialState */10] = (function () {
      return /* record */[/* count */0];
    });
  newrecord[/* reducer */12] = (function (action, state) {
      if (action !== 0) {
        return /* Update */Block.__(0, [/* record */[/* count */state[/* count */0] - 1 | 0]]);
      } else {
        return /* Update */Block.__(0, [/* record */[/* count */state[/* count */0] + 1 | 0]]);
      }
    });
  return newrecord;
}

exports.component = component;
exports.make = make;
/* component Not a pure module */