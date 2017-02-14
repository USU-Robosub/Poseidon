require 'socket'

def start()
    procPath = "../../BoneCentral/Peripherals/Release"
    @server = TCPServer.open(25565)
    @child = Thread.new {
        system("./#{procPath}/Peripherals --dispatcherPort=25565")
    }
end

def finish()
    @child.join
    @server.close
end


start()
client = @server.accept

client.puts("faceDirection 0 0\n")
client.puts("thrustForward 1 1\n")
client.puts("dive 1 1\n")
client.puts("goDirection 0 0 0\n")

client.puts("exit")

client.close
finish()