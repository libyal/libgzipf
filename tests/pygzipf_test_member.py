#!/usr/bin/env python
#
# Python-bindings member type test script
#
# Copyright (C) 2019-2025, Joachim Metz <joachim.metz@gmail.com>
#
# Refer to AUTHORS for acknowledgements.
#
# This program is free software: you can redistribute it and/or modify
# it under the terms of the GNU Lesser General Public License as published by
# the Free Software Foundation, either version 3 of the License, or
# (at your option) any later version.
#
# This program is distributed in the hope that it will be useful,
# but WITHOUT ANY WARRANTY; without even the implied warranty of
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
# GNU General Public License for more details.
#
# You should have received a copy of the GNU Lesser General Public License
# along with this program.  If not, see <https://www.gnu.org/licenses/>.

import argparse
import os
import sys
import unittest

import pygzipf


class MemberTypeTests(unittest.TestCase):
  """Tests the member type."""

  def test_get_modification_time(self):
    """Tests the get_modification_time function and modification_time property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    gzipf_file = pygzipf.file()

    gzipf_file.open(test_source)

    try:
      if not gzipf_file.number_of_members:
        raise unittest.SkipTest("missing members")

      gzipf_member = gzipf_file.get_member(0)
      self.assertIsNotNone(gzipf_member)

      modification_time = gzipf_member.get_modification_time()
      self.assertIsNotNone(modification_time)

      self.assertIsNotNone(gzipf_member.modification_time)

    finally:
      gzipf_file.close()

  def test_get_name(self):
    """Tests the get_name function and name property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    gzipf_file = pygzipf.file()

    gzipf_file.open(test_source)

    try:
      if not gzipf_file.number_of_members:
        raise unittest.SkipTest("missing members")

      gzipf_member = gzipf_file.get_member(0)
      self.assertIsNotNone(gzipf_member)

      name = gzipf_member.get_name()
      self.assertIsNotNone(name)

      self.assertIsNotNone(gzipf_member.name)

    finally:
      gzipf_file.close()

  def test_get_comments(self):
    """Tests the get_comments function and comments property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    gzipf_file = pygzipf.file()

    gzipf_file.open(test_source)

    try:
      if not gzipf_file.number_of_members:
        raise unittest.SkipTest("missing members")

      gzipf_member = gzipf_file.get_member(0)
      self.assertIsNotNone(gzipf_member)

      comments = gzipf_member.get_comments()
      self.assertIsNotNone(comments)

      self.assertIsNotNone(gzipf_member.comments)

    finally:
      gzipf_file.close()

  def test_get_operating_system(self):
    """Tests the get_operating_system function and operating_system property."""
    test_source = getattr(unittest, "source", None)
    if not test_source:
      raise unittest.SkipTest("missing source")

    gzipf_file = pygzipf.file()

    gzipf_file.open(test_source)

    try:
      if not gzipf_file.number_of_members:
        raise unittest.SkipTest("missing members")

      gzipf_member = gzipf_file.get_member(0)
      self.assertIsNotNone(gzipf_member)

      operating_system = gzipf_member.get_operating_system()
      self.assertIsNotNone(operating_system)

      self.assertIsNotNone(gzipf_member.operating_system)

    finally:
      gzipf_file.close()


if __name__ == "__main__":
  argument_parser = argparse.ArgumentParser()

  argument_parser.add_argument(
      "source", nargs="?", action="store", metavar="PATH",
      default=None, help="path of the source file.")

  options, unknown_options = argument_parser.parse_known_args()
  unknown_options.insert(0, sys.argv[0])

  setattr(unittest, "source", options.source)

  unittest.main(argv=unknown_options, verbosity=2)
