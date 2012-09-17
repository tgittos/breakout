# A file to generate the header

class Header
  
  PATH = "lit/include"
  EXCLUDE_FROM_ALL = false

  def self.generate(file)
    if File.exists? "#{PATH}/#{file}.hpp.lit"
      puts "Not overwriting file #{PATH}/#{file}.hpp.lit"
      return
    end 

    File.open("#{PATH}/#{file}.hpp.lit", "w") do |f|
      f.write <<-EOS
== The class ==
-
class #{file} {
  public:
  #{file}(){};
  ~#{file}(){};
};
-

== Includes ==
-
-

== Include guard ==
-
#ifndef #{file.underscore.upcase}_H
#define #{file.underscore.upcase}_H

Includes.

The class.

#endif
-

== @#{file}.hpp ==
Include guard.
      EOS
    end
  end

end