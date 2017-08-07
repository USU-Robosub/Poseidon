void process(IHub* hub, std::string connection, json message){
  hub->send("LOCAL", json({ // "LOCAL" will use a loop connection to use Router to send to correct outbound connection
    {"target": "bob"},
    {"data": "stuff"}
  }).dump()),
}
