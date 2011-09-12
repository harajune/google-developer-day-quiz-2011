
lines1 = []

open(ARGV[0], "r") do |file|
    file.each do |line|
        lines1 << line.strip
    end
end

open(ARGV[1], "r") do |file|
    counter = 0
    file.each do |line|
        line.strip!

        if line.size < 1
            puts lines1[counter]
        elsif lines1[counter].nil? or lines1[counter].size < 1
            puts line

        elsif line.size > lines1[counter].size
            puts lines1[counter]
        else
            puts line
        end

        counter += 1
    end
end
