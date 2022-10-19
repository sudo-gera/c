#!/usr/bin/env lua
require 'socket'
require 'copas'

assert(arg[1],"Must pass host and port to listen")
assert(arg[2],"Must pass host and port to proxy")

local config = {
    newhost=string.gsub(arg[1],"([^:]+):(%d+)","%1"),
    newport=string.gsub(arg[1],"([^:]+):(%d+)","%2"),
    oldhost=string.gsub(arg[2],"([^:]+):(%d+)","%1"),
    oldport=string.gsub(arg[2],"([^:]+):(%d+)","%2")
}

print("Proxying from ".. config.newhost .. ":" .. config.newport
              .." to ".. config.oldhost .. ":" .. config.oldport)

function log(s)
    print(s)
end

local server = socket.bind(config.newhost,config.newport)

local headers_parsers = {
    [ "connection" ]= function(h)
        return "Connection: close"
    end,
    [ "host" ]= function(h)
        return "Host: " .. config.oldhost ..":"..config.oldport
    end,
    [ "location" ]= function(h)
        local  new, old ;
        if config.newport == "80" then new = config.newhost else new = config.newhost .. ":" .. config.newport end
        if config.oldport == "80" then old = config.oldhost else old = config.oldhost .. ":" .. config.oldport end
        return string.gsub(h,old,new,1);
    end
}

function get_method(l)
    return string.gsub(l,"^(%w+).*$","%1")
end

function parse_header(l)
    local head, last
    for k in string.gmatch(l,"([^:%s]+)%s?:") do head = string.lower(k) ; break end
    if headers_parsers[head] ~= nil then
        l =  headers_parsers[head](l)
    end
    if string.len(l) == 0 then last = true end
    return l .. "\r\n",last, l
end

function pass_headers(reader,writer,dir)
    local method, len 
    while true do
        local req = reader:receive()
        if dir == ">" and method == nil then method = get_method(req) end
        if string.lower(string.sub(req,0,14)) == "content-length" then len = string.gsub(req,"[^:]+:%s*(%d+)","%1") end
        local header, last, h = parse_header(req)
        writer:send(header)
        log(dir .. " " .. h)
        if last then break end
    end
    return method, len
end

function pass_body(reader,writer, len, dir)
    if len == nil then
        while true do
            local res, err, part = reader:receive(512)
            if err == "closed" or err == 'timeout' then
                if part ~= nil then log(part); writer:send(part) end
                break
            end
            log(res)
            writer:send(res)
        end
    else
        if len == 0 then return nil end
        local res, err, part =  reader:receive(len)
        log(res)
        writer:send(res)
    end
end

function handler(sk8)
    local c = copas.wrap(sk8)
    local s = socket.connect(config.oldhost,config.oldport)
    s:settimeout(10)
    local method,len = pass_headers(c,s,">")
    if len ~= nil then pass_body(c,s,tonumber(len),">") end
    local _, len2 = pass_headers(s,c,"<")
    pass_body(s,c,len2,"<")
    s:close()
end

copas.addserver(server, handler)
copas.loop()
