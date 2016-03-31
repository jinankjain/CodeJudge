# -*- coding: utf-8 -*-
from __future__ import unicode_literals

from django.db import models, migrations
import datetime
from django.utils.timezone import utc


class Migration(migrations.Migration):

    dependencies = [
        ('judge', '0012_auto_20160330_1621'),
    ]

    operations = [
        migrations.RemoveField(
            model_name='problem',
            name='contest',
        ),
        migrations.AddField(
            model_name='problem',
            name='contest',
            field=models.ForeignKey(default=datetime.datetime(2016, 3, 30, 10, 54, 35, 983357, tzinfo=utc), to='judge.Contest'),
            preserve_default=False,
        ),
    ]
