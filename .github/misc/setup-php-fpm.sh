#!/bin/bash
#
# Helper script for Github Actions to tweak php-fpm without bloating the
# workflow file.

# This script handles one required numeric parameter - the PHP version.
OLDPHP=$(echo "$1 < 7" | /usr/bin/bc -l)

# Apache mpm_event refuses to work with older PHP versions, we have to switch to
# mpm_prefork for 5.x. The paths to config files differ for 5.x as set up by
# shivammathur/setup-php@v2
if [ $OLDPHP -eq 1 ]; then
  sudo a2dismod mpm_event
  sudo a2enmod mpm_prefork
  CONFPATHS=$(ls /usr/local/php/*/etc/php-fpm.conf)
else
  CONFPATHS=$(ls /etc/php/*/fpm/pool.d/www.conf)
fi

# Configure php-fpm to run as user "runner". That makes moving files around
# obsolete. Additionally tweak it for better performance, start and allow more
# child processes. This is done in all config files, sed is fast.
sudo sed -i -e 's/user = www-data/user = runner/' \
  -e 's/listen.owner = www-data/listen.owner = runner/' \
  -e 's/pm.max_children = 5/pm.max_children = 15/' \
  -e 's/pm.start_servers = 2/pm.start_servers = 4/' \
  -e 's/pm.min_spare_servers = 1/pm.min_spare_servers = 2/' \
  -e 's/pm.max_spare_servers = 3/pm.max_spare_servers = 4/' \
  $CONFPATHS

exit 0
