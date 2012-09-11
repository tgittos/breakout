# A file to generate the class

class Klass

  PATH = "lit/src"
  EXCLUDE_FROM_ALL = false

  def self.generate(file)
    if File.exists? "#{PATH}/#{file}.cpp.lit"
      puts "Not overwriting file #{PATH}/#{file}.cpp.lit"
      return
    end 

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