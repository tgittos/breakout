# A file to generate the class, header and test

class Clt

  require 'class.rb'
  require 'header.rb'
  require 'unittest.rb'

  def self.generate(file)
    Klass.generate(file)
    Header.generate(file)
    Unittest.generate(file)
  end

end