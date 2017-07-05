/^# Packages using this file: / {
  s/# Packages using this file://
  ta
  :a
  s/ augeas / augeas /
  tb
  s/ $/ augeas /
  :b
  s/^/# Packages using this file:/
}
