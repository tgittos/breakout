# A file to generate a makefile

class Makefile

  BASE_FILE = 'Makefile.base'
  OUTPUT_FILE = 'Makefile'
  EXCLUDE_FROM_ALL = true

  def self.generate
    # rm the existing makefile, if one exists
    File.delete(OUTPUT_FILE) if File.exists? OUTPUT_FILE

    # read in the base instructions
    file = File.open(BASE_FILE, "r")
    base = file.read
    file.close

    # construct rules to build every header from it's literati file
    includes = Dir.entries("lit/include").reject{|f| f =~ /^\./}.collect do |f|
      (@includes_list ||= []) << f
      <<-EOS
#{get_name f}.hpp:
\tliterati tangle -o src/. lit/include/$@.lit
      EOS
    end

    # construct rules to build every mock from it's literati file
    mocks = Dir.entries("lit/mocks").reject{|f| f =~ /^\./}.collect do |f|
      (@includes_list ||= []) << f
      <<-EOS
#{get_name f}.hpp:
\tliterati tangle -o src/. lit/mocks/$@.lit
      EOS
    end

    # construct rules to build every source file from it's literati file
    game_sources = Dir.entries("lit/src").reject{|f| f =~ /^\./}.collect do |f|
      (@game_sources_list ||= []) << f
      <<-EOS
#{get_name f}.cpp:
\tliterati tangle -o src/. lit/src/$@.lit
      EOS
    end

    # construct rules to build every game object from it's header/source file
    game_objects = Dir.entries("lit/src").reject{|f| f =~ /^\./}.collect do |f|
      (@game_objects_list ||= []) << f
      <<-EOS
#{get_name f}.o: #{header?(get_name f)} #{get_name f}.cpp
\t$(CXX) $(IFLAGS) $(CXXFLAGS) -c -o $@ src/#{get_name f}.cpp
      EOS
    end

    # construct rules to build every test source file from it's literati file
    test_sources = Dir.entries("lit/test").reject{|f| f =~ /^\./}.collect do |f|
      (@test_sources_list || []) << f
      <<-EOS
#{get_name f}.cpp:
\tliterati tangle -o src/. lit/test/$@.lit
      EOS
    end

    # construct rules to build every test object from the gtest/game object/test source file
    test_objects = Dir.entries("lit/test").reject{|f| f =~ /^\./}.collect do |f|
      (@test_objects_list || []) << f
      <<-EOS
#{get_name f}.o: #{get_name f}.cpp #{get_game_name(get_name f)}.hpp $(GTEST_HEADERS)
\t$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) -c $(SRC_DIR)/#{get_name f}.cpp -o $@
      EOS
    end

    # construct rules to build every test binary from test objects/gtest
    test_binaries = Dir.entries("lit/test").reject{|f| f =~ /^\./}.collect do |f|
      <<-EOS
#{get_name f}: #{get_name f}.o #{get_game_name(get_name f)}.o gtest_main.a libgmock.a
\t$(CXX) $(IFLAGS) $(GTEST_IFLAGS) $(GMOCK_IFLAGS) $(CXXFLAGS) #{get_game_name(get_name f)}.o #{get_name f}.o gtest_main.a libgmock.a -o $@
      EOS
    end

    # write all the rules + the base out to a new Makefile
    File.open("Makefile", "w") do |f|
      f.write base
      f.write "\n"
      f.write includes.join("\n")
      f.write "\n"
      f.write mocks.join("\n")
      f.write "\n"
      f.write game_sources.join("\n")
      f.write "\n"
      f.write game_objects.join("\n")
      f.write "\n"
      f.write test_sources.join("\n")
      f.write "\n"
      f.write test_objects.join("\n")
      f.write "\n"
      f.write test_binaries.join("\n")
    end
  end

  private

  def self.get_name(f)
    f.split('.').first
  end

  def self.get_game_name(f)
    f.split('_').first
  end

  def self.header?(f)
    result = @includes_list.select{|i| i =~ /^#{f}/}.first
    return "#{get_name(result)}.hpp" if result
    return ""
  end

end