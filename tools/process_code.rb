#!/usr/bin/env ruby

ProjectDir = File.dirname(__FILE__)+"/.."
FileHeader = %{/*-
Minimalistic and Modular OpenGL C++ Framework
The GNU General Public License v3.0
-*/}
LineEnd = "\n"

def processFile(path)
    out = ""

    inHeader = false
    firstLine = true
    headerOutputted = false

    File.open(path).each do |l|
        inHeader = true if (firstLine && l =~ /^\/\*\-/)
        firstLine = false

        # skip and rewrite comment header
        if inHeader && l =~ /\*\/$/
            inHeader = false
            next
        end
        next if inHeader

        out += FileHeader + LineEnd if !headerOutputted
        headerOutputted = true

        # fix indend
        if l =~ /^(\s*)(\S.*)$/
            spaceChars = $1
            code = $2

            spaceWidth = 0
            spaceChars.each_char do |c|
                if c == "\t"
                    spaceWidth += 4
                else
                    spaceWidth += 1
                end
            end
            #puts "- line '#{l}' space chars '#{spaceChars}' space wid #{spaceWidth}"
            spaceWidth = ((spaceWidth/4.0).round * 4).to_i

            out += (" " * spaceWidth) + code + LineEnd
        elsif l =~ /^(.*)$/
            #puts "passthrough '#{$1}'"
            out += $1 + LineEnd
        end
    end

    File.open(path, 'w') { |f| f.write(out) }
end

Dir[ProjectDir+"/src/**/*"].each do |path|
    # skip files other then source and header files
    next if path !~ /.*\.(cp*|hp*)$/

    processFile path
end

Dir[ProjectDir+"/examples/**/*"].each do |path|
    # skip files other then source and header files
    next if path !~ /.*\.(cp*|hp*)$/

    processFile path
end
