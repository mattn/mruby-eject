MRuby::Gem::Specification.new('mruby-eject') do |spec|
  spec.license = 'MIT'
  spec.authors = 'mattn'

  if ENV['OS'] == 'Windows_NT'
    spec.linker.libraries << 'winmm'
  end
end
