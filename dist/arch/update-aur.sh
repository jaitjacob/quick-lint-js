#!/bin/sh

# Copyright (C) 2020  Matthew "strager" Glazar
# See end of file for extended copyright information.

set -e
set -u

if [ "${#}" -ne 1 ]; then
  printf 'usage: %s /path/to/quick-lint-js-aur\n' "${0}" >&2
  exit 1
fi

qljsaur="${1}"
here="$(dirname "${0}")"

cp "${here}/PKGBUILD-release" "${qljsaur}/PKGBUILD"
updpkgsums "${qljsaur}/PKGBUILD"
makepkg --printsrcinfo "${qljsaur}/PKGBUILD" >"${qljsaur}/.SRCINFO"

cd "${qljsaur}"
git add PKGBUILD .SRCINFO
printf '\nChanges staged. Please commit and push.\n' >&2

# quick-lint-js finds bugs in JavaScript programs.
# Copyright (C) 2020  Matthew "strager" Glazar
#
# This file is part of quick-lint-js.
#
# quick-lint-js is free software: you can redistribute it and/or modify
# it under the terms of the GNU General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# quick-lint-js is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU General Public License
# along with quick-lint-js.  If not, see <https://www.gnu.org/licenses/>.
