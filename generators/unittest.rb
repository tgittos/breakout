# A file to generate a unit test

class Unittest

  PATH = "lit/test"
  EXCLUDE_FROM_ALL = true

  def self.generate(file)
    puts "Not overwriting file #{file}.cpp.lit" and return if File.exists? "#{PATH}/#{file}.cpp.lit"

    File.open("#{PATH}/#{file}.cpp.lit", "w") do |f|
      f.write <<-EOS
== Includes ==
-
#include "gtest/gtest.h"
#include "gmock/gmock.h"
#include "Mock#{file.split('_').first}.hpp"
-

== Wrapper ==
-
Includes.
-

== @#{file}.cpp ==
Wrapper.
      EOS
    end
  end

end