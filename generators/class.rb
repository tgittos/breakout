# A file to generate the class

class Klass

  PATH = "lit/src"
  EXCLUDE_FROM_ALL = false

  def self.generate(file)
    puts "Not overwriting file #{file}.cpp.lit" and return if File.exists? "#{PATH}/#{file}.cpp.lit"

    File.open("#{PATH}/#{file}.cpp.lit", "w") do |f|
      f.write <<-EOS
== Includes ==
-
#include "#{file}.hpp"
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