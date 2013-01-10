MRuby::Gem::Specification.new('mruby-eject') do |spec|
  spec.license = 'MIT'
  spec.authors = 'mattn'

  if ENV['OS'] == 'Windows_NT'
    spec.mruby_libs = '-lwinmm'
  end
end
