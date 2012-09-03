# A file to generate the header

class Header
  
  PATH = "lit/include"
  EXCLUDE_FROM_ALL = false

  def self.generate(file)
    puts "Not overwriting file #{file}.hpp.lit" and return if File.exists? "#{PATH}/#{file}.hpp.lit"

    File.open("#{PATH}/#{file}.hpp.lit", "w") do |f|
      f.write <<-EOS
== The class ==
-
class #{file} {
  
};
-

== Include guard ==
-
#ifndef #{file.underscore.upcase}_H
#define #{file.underscore.upcase}_H

The class.

#endif
-

== @#{file}.hpp ==
Include guard.
      EOS
    end
  end

end