# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('judge', '0008_auto_20160117_2351'),
    ]

    operations = [
        migrations.RenameField(
            model_name='problem',
            old_name='points',
            new_name='marks',
        ),
    ]
