bind -qa $home/bin/rc /bin
bind -qa $home/bin/$cputype /bin
bind -b $home/go/bin /bin
bind -b $home/prg/go/bin /bin
GOPATH=$home/prg/go
mount -qC /srv/boot /n/other other
bind -qc /n/other/usr/$user/tmp $home/tmp
bind -c $home/tmp /tmp
font=/lib/font/bit/vga/unicode.font
switch($service){
case terminal
	webcookies
	webfs
	plumber
	echo -n accelerated > '#m/mousectl'
	echo -n 'res 3' > '#m/mousectl'
	prompt=('term% ' '	')
	fn term%{ $* }
	auth/factotum -n
	rio -s -i riostart
case cpu
	bind /mnt/term/dev/cons /dev/cons
	bind -q /mnt/term/dev/consctl /dev/consctl
	>[2] /dev/null {
		cp /dev/sysname /mnt/term/dev/label
		if(wsys=`{cat /mnt/term/env/wsys})
			wsys=/mnt/term^$wsys
	} 
	bind -a /mnt/term/dev /dev
	prompt=('sav-cpu% ' '	')
	fn cpu%{ $* }
	if(! test -e /mnt/term/dev/wsys){
		# call from drawterm
		if(test -e /mnt/term/dev/secstore){
			auth/factotum -n
			read -m /mnt/term/dev/secstore >/mnt/factotum/ctl
			echo >/mnt/term/dev/secstore
		}
		if not
			auth/factotum
		webcookies
		webfs
		plumber
		auth/factotum -n
		rio -s -i riostart
	}
case con
	prompt=('cpu% ' '	')
}
