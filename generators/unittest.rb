# A file to generate a unit test

class Unittest

  PATH = "lit/test"
  EXCLUDE_FROM_ALL = true

  def self.generate(file)
    if File.exists? "#{PATH}/#{file}_unittest.cpp.lit"
      puts "Not overwriting file #{PATH}/#{file}_unittest.cpp.lit"
      return
    end 

    File.open("#{PATH}/#{file}_unittest.cpp.lit", "w") do |f|
      f.write <<-EOS
== Includes ==
-
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Mock#{file}.hpp"
-

== Wrapper ==
-
Includes.
-

== @#{file}_unittest.cpp ==
Wrapper.
      EOS
    end
  end

end