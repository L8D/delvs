#!/usr/bin/env ruby
require 'io/console'

class RuntimeData
  attr_accessor :c
  attr_accessor :v
  attr_accessor :i
  attr_accessor :f
  attr_accessor :p

  def initialize
    @c = ""
    @i = 0
    @v = Array.new 30000, 0
    @p = 15000
    @f = ""
  end
end

def dummy_lexer d
  while d.i <= d.c.length do
    return d.i if d.c[d.i] == ']'
    d.i += 1
  end
end

def lexer d
  while d.i <= d.c.length do
    case d.c[d.i]
      when '>' then
        d.p += 1

      when '<' then
        d.p -= 1

      when '+' then
        d.v[d.p] += 1

      when '-' then
        d.v[d.p] -= 1

      when '.' then
        print d.v[d.p].chr

      when ',' then
        d.v[d.p] = IO.console.getch.ord

      when '[' then
        r = d.i + 1
        d.i = dlexer d if !d.v[d.p]
        while d.v[d.p] != 0 do
          d.i = r
          d = lexer d
        end

      when ']' then
        return d
      
      else
        # Everything else is comments
    end
    d.i += 1
  end
end

# example usage:
# data = RuntimeData.new
# data.c = "+++++ +++++ [ > +++++ +++++ > + << - ] > ++++ . + . > ."
# lexer data
