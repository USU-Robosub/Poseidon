require Dir.pwd + "/Server"

test = Server.new
test.setPort 4322
test.start
