type status =
  | Ok
  | Fetching
  | Error;

type state = {
  gifs: list(string),
  status,
};

type action =
  | StartFetching
  | FinishFetching(option(string));

let component = ReasonReact.reducerComponent("GifLoader");

let getGifUrlFromJSON = json =>
  Json.Decode.(
    json
    |> field("data", json =>
         json
         |> field("images", json =>
              json |> field("source", json => json |> field("url", string))
            )
       )
  );

/* api.giphy.com/v1/gifs/random?api_key=cuHpcSHH4zEjGjn0szj3cTBTmAH3dwAn */
let make = _children => {
  ...component,
  initialState: () => {gifs: [], status: Ok},
  reducer: (action, state) =>
    switch (action) {
    | FinishFetching(newGif) =>
      switch (newGif) {
      | None => ReasonReact.Update({...state, status: Error})
      | Some(gifUrl) =>
        ReasonReact.Update({
          gifs: List.append(state.gifs, [gifUrl]),
          status: Ok,
        })
      }
    | StartFetching =>
      ReasonReact.UpdateWithSideEffects(
        {...state, status: Fetching},
        (
          self =>
            ignore(
              Js.Promise.(
                Fetch.fetch(
                  "https://api.giphy.com/v1/gifs/random?api_key=cuHpcSHH4zEjGjn0szj3cTBTmAH3dwAn",
                )
                |> then_(Fetch.Response.json)
                |> then_(json => {
                     let gifUrl = getGifUrlFromJSON(json);
                     self.send(FinishFetching(Some(gifUrl))) |> resolve;
                   })
                |> catch(_err => self.send(FinishFetching(None)) |> resolve)
              ),
            )
        ),
      )
    },
  render: self => {
    let buttonTitle =
      switch (self.state.status) {
      | Ok => "Fetch random GIF"
      | Error => "Error occured! Refetch"
      | Fetching => "Fetching..."
      };
    let gifs =
      List.map(gif => <div key=gif> <img src=gif /> </div>, self.state.gifs);
    <div>
      (ReasonReact.arrayToElement(Array.of_list(gifs)))
      <button onClick=(_event => self.send(StartFetching))>
        (ReasonReact.stringToElement(buttonTitle))
      </button>
    </div>;
  },
};