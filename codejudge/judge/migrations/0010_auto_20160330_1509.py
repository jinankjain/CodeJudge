# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations


class Migration(migrations.Migration):

    dependencies = [
        ('judge', '0009_auto_20160330_1508'),
    ]

    operations = [
        migrations.RenameField(
            model_name='solution',
            old_name='points',
            new_name='marks',
        ),
    ]
