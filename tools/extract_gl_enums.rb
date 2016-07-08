#!/usr/bin/env ruby

ProjectDir = File.dirname(__FILE__)+"/.."
LineEnd = "\n"

print <<-eos
// Generated using /tools/extract_gl_enums.rb

#include "debug/glad.h"
#include <map>
#include <string.h>

const char* GLEnumToString(unsigned e) 
{
    static bool inited = false;
    typedef std::map<GLenum, const char*> EnumStrMap;
    static EnumStrMap m;

    if (!inited) { 
        inited = true;

eos

File.open(ProjectDir + "/deps/glad/release/glad.h").each do |l| 
    if l =~ /#define\s+(GL_[_A-Z0-9]+)\s+([0-9a-fA-Fx]+)/
        puts "        m[#{$2}] = \"#{$1}\";" if $2.to_i(16) >= 256
    end
end

puts <<-eos
    
        // ensure true and false
        // m[0] = "GL_FALSE";
        // m[1] = "GL_TRUE";
    }

    const char* str = m[e];
    if (!str) {
        static char buff[32];
        sprintf(buff, "0x%X", e);
        return buff;
    }

    return str;
}
eos

