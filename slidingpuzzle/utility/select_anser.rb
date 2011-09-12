require "set"

L=72187
R=81749
U=72303
D=81778

lines = []
score = []

al = 0
au = 0
ar = 0
ad = 0

open(ARGV[0], "r") do |file|
    counter = 0
    file.each do |li|
        li.strip!

        lines << li

        l = 0
        u = 0
        r = 0
        d = 0

        li.each_byte do |b|
            case b
            when 0x4c
                l += 1

            when 0x55
                u += 1

            when 0x52
                r += 1

            when 0x44
                d += 1

            else
                STDERR.puts b
            end
        end

        score << [counter, li.size, l, r, u, d]

        al += l
        ar += r
        au += u
        ad += d

        counter += 1
    end
end

score.sort! {|a,b| b[1] <=> a[1]}

delete_set = Set.new
score.each do |s|
    if al <= L and ar <= R and au <= U and ad <= D
        break
    end

    al -= s[2]
    ar -= s[3]
    au -= s[4]
    ad -= s[5]

    delete_set << s[0]
end

lines.each_index do |ind|
    if delete_set.include?(ind)
        puts ""
        next
    end

    puts lines[ind]
end

(5000-lines.size).times do 
    puts ""
end

