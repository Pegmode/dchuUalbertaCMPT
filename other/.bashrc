# User bashrc file:
# $Id: Bashrc.user 2614 2014-09-30 20:20:00Z johnb $

# Copyright (c) 2012 University of Alberta Department of Computing Science <helpdesk@cs.ualberta.ca>
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
# WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
# MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
# ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
# WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
# ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
# OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
#


# source the standard bashrc
# DON'T TOUCH THIS LINE
source /usr/local/rcfiles/Bashrc.global


# If you want to alter your path, do it like this:
#
# PATH=$PATH\:some_directories
# export PATH
#
# The same can be done for MANPATH and INFOPATH.
# It is _STRONGLY_ recommended that you add your stuff _AFTER_ the original
# path.
#
# Stuff you might want to add:
# $HOME/bin
#
# Note that most paths are architecture specific, so you should use the
# case statement below.


# If you need to do any architecture specific stuff (including *PATH stuff),
# do it within a case statement like this:
#
# ( The sysadmins have defined a variable called DISTRO, that if you
# sourced the global RC file above it should be defined. )

#case $DISTRO in
#    slackware122)  # Any machine running Slackware 12.2
#        # Slackware 12.2 stuff
#	;;
#    ubuntu1204)  # Ubuntu 12.04
#        # Ubuntu 12.04 stuff
#	;;
#    undefined)  # if something has gone wrong and DISTRO
#                # is 'undefined' then do something safe.
#	;;
#esac


# don't like emacs?  uncomment and change "emacs" to something else (like vi!)
#export EDITOR=emacs
#export VISUAL=emacs


# prompt is currently set to: user@host:currentdir>
# read the bash man page if you want to change it
#export PS1='\u@\h:\w>'


# output redirect (>) to existing files is disabled by default
# uncomment the next line to allow clobbering
# make sure you know what you are getting into!
#set +o noclobber


# Functions
# define any functions you want here


# here are the aliases we have already defined for you
# feel free to change or unalias them or define new ones
#alias mv="mv -i"
#alias cp="cp -i"
#alias rm="rm -i"
#alias mail="elm"
#alias run="source"
#alias ll="ls -l"
#alias la="ls -la"
#alias pwd='echo $PWD'
#alias md='mkdir'
#alias rd='rmdir'
alias g="gcc -Wall -std=c99" #GCC standard for CMPUT 201
alias ls="ls --color" #add color for ssh term
alias gem5S="nice -n 13 ~/programs/gem5/build/ARM/gem5.opt" #run gem5 simuation with low scheduling priority, use like : gem5S configs/spec/run.py -b bzip 
