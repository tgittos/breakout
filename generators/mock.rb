# A file to generate the mock

class Mock

  PATH = "lit/mocks"
  EXCLUDE_FROM_ALL = false

  def self.generate(file)
    if File.exists? "#{PATH}/Mock#{file}.hpp.lit"
      puts "Not overwriting file #{PATH}/Mock#{file}.hpp.lit"
      return
    end 
    
    File.open("#{PATH}/Mock#{file}.hpp.lit", "w") do |f|
      f.write <<-EOS
== The class ==
-
class Mock#{file} : public #{file} {
  
};
-

== Includes ==
-
#include "gmock/gmock.h"
#include "#{file}.hpp"
-

== Include guard ==
-
#ifndef MOCK_#{file.underscore.upcase}_H
#define MOCK_#{file.underscore.upcase}_H

Includes.

The class.

#endif
-

== @Mock#{file}.hpp ==
Include guard.
      EOS
    end
  end
end