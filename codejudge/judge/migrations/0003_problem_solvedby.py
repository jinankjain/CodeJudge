# -*- coding: utf-8 -*-
# Generated by Django 1.9 on 2016-04-04 16:58
from __future__ import unicode_literals

from django.db import migrations, models


class Migration(migrations.Migration):

    dependencies = [
        ('judge', '0002_remove_problem_solvedby'),
    ]

    operations = [
        migrations.AddField(
            model_name='problem',
            name='solvedBy',
            field=models.PositiveSmallIntegerField(default=0),
        ),
    ]
