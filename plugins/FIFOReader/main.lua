package.path = package.path .. ";/usr/share/lua/5.4/?.lua"
lunajson = require 'lunajson'
fcntl = require 'posix.fcntl'
stdio = require 'posix.stdio'
poll = require 'posix.poll'

function initUi()
    app.registerBackgroundTask("listenSocket")
end

function listenSocket()
    local fd = fcntl.open("/tmp/xournalpp.fifo", fcntl.O_RDONLY | fcntl.O_NONBLOCK)
    if not poll.rpoll(fd, 300) then
        return
    end
    local file = stdio.fdopen(fd, 'r')
    if not file then
        return
    end
    local line = file:read()
    file:close()
    if not line then
        return
    end

    local parsed = lunajson.decode( line )
    app[parsed['api_fun']](table.unpack(parsed['parameters']))
end
