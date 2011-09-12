
u = 0
d = 0
l = 0
r = 0

open(ARGV[0], "r") do |file|
    file.each_byte do |b|
        case b
        when 0x4c
            l += 1

        when 0x55
            u += 1

        when 0x52
            r += 1

        when 0x44
            d += 1

        when 0x0a

        else
            STDERR.puts b
        end
    end
end

puts "L:#{l}\tR:#{r}\tU:#{u}\tD:#{d}"
