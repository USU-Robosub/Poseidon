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

client.puts("faceDirection\n0 0")
client.puts("thrustForward\n1 1")
client.puts("dive\n1 1")
client.puts("goDirection\n0 0 0")

client.puts("exit")

client.close
finish()