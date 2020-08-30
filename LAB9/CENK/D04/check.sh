#!/bin/bash
declare -a lines
# Load file into array
let i=0
while IFS= read -r line_data; do
    lines[i]="${line_data}"
    ((++i))
done < $1
#seperated fields
declare -a ip_list
args=( "$@" )
for line in "${lines[@]}" ; do words=($line)
	if [ ${words[3]} = "POST" ] ; then
		if [ ${words[5]} = "200" ]; then
			if [[ ${words[2]} =~ "[$2"* ]] ; then
				if [[ $@ =~ ${words[1]} ]] ; then
					if [[ ${ip_list[*]} != ${words[0]} ]] ; then
						ip_list+=( "${words[0]}" )
					fi
				fi
			fi
		fi
	fi
done
for ip in "${ip_list[@]}" ; do echo $ip ; done
exit 0
