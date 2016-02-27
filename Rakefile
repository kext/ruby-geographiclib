require 'rubygems'
require 'rubygems/gem_runner'

Name = 'geographiclib'

gemspecfile = "#{Name}.gemspec"
gemspec = Gem::Specification.load(gemspecfile)
gemfile = "#{Name}-#{gemspec.version}.gem"

file gemfile => [gemspecfile, gemspec.files].flatten do
  Gem::GemRunner.new.run ['build', gemspecfile]
end

task :default => gemfile

task :install => [:default] do
  Gem::GemRunner.new.run ['install', "./#{gemfile}"]
end

task :clean do
  system 'rm -f *.gem'
end
